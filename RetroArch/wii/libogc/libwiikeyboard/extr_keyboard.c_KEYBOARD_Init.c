#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ st_size; } ;
typedef  int s32 ;
typedef  scalar_t__ keyPressCallback ;
struct TYPE_5__ {scalar_t__ tail; scalar_t__ head; } ;
struct TYPE_4__ {scalar_t__ layout; } ;

/* Variables and functions */
 int CONF_GetLanguage () ; 
#define  CONF_LANG_DUTCH 136 
#define  CONF_LANG_FRENCH 135 
#define  CONF_LANG_GERMAN 134 
#define  CONF_LANG_ITALIAN 133 
#define  CONF_LANG_JAPANESE 132 
#define  CONF_LANG_KOREAN 131 
#define  CONF_LANG_SIMP_CHINESE 130 
#define  CONF_LANG_SPANISH 129 
#define  CONF_LANG_TRAD_CHINESE 128 
 scalar_t__ IPC_OK ; 
 int /*<<< orphan*/  KBD_THREAD_PRIO ; 
 int /*<<< orphan*/  KBD_THREAD_STACKSIZE ; 
 scalar_t__ KB_DE ; 
 scalar_t__ KB_ES ; 
 scalar_t__ KB_FR ; 
 scalar_t__ KB_IT ; 
 scalar_t__ KB_JP ; 
 scalar_t__ KB_NL ; 
 scalar_t__ KB_NONE ; 
 scalar_t__ KB_US ; 
 int /*<<< orphan*/  KEYBOARD_FlushEvents () ; 
 int LWP_CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_JoinThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 size_t STD_IN ; 
 int /*<<< orphan*/  USBKeyboard_Close () ; 
 int /*<<< orphan*/  USBKeyboard_Deinitialize () ; 
 scalar_t__ USBKeyboard_Initialize () ; 
 scalar_t__ USB_Initialize () ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ _get_keymap_by_name (char*) ; 
 int /*<<< orphan*/  _kbd_buf_stack ; 
 int /*<<< orphan*/  _kbd_buf_thread ; 
 int /*<<< orphan*/  _kbd_buf_thread_func ; 
 int /*<<< orphan*/  _kbd_stack ; 
 int /*<<< orphan*/  _kbd_thread ; 
 int /*<<< orphan*/  _kbd_thread_func ; 
 int _kbd_thread_quit ; 
 int _kbd_thread_running ; 
 TYPE_3__ _keyBuffer ; 
 int /*<<< orphan*/  _queue ; 
 scalar_t__ _readKey_cb ; 
 int /*<<< orphan*/  _sc_map ; 
 int /*<<< orphan*/  _sc_maplen ; 
 TYPE_1__ _ukbd_keymapdata ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ ** devoptab_list ; 
 int /*<<< orphan*/  fstat (int,struct stat*) ; 
 scalar_t__ isalpha (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  std_in ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ wskbd_load_keymap (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

s32 KEYBOARD_Init(keyPressCallback keypress_cb)
{
	int fd;
	struct stat st;
	char keymap[64];
	size_t i;

	if (USB_Initialize() != IPC_OK)
		return -1;

	if (USBKeyboard_Initialize() != IPC_OK) {
		return -2;
	}

	if (_ukbd_keymapdata.layout == KB_NONE) {
		keymap[0] = 0;
		fd = open("/wiikbd.map", O_RDONLY);

		if ((fd > 0) && !fstat(fd, &st)) {
			if ((st.st_size > 0) && (st.st_size < 64) &&
				(st.st_size == read(fd, keymap, st.st_size))) {
				keymap[63] = 0;
				for (i = 0; i < 64; ++i) {
					if ((keymap[i] != '-') && (isalpha((int)keymap[i]) == 0)) {
						keymap[i] = 0;
						break;
					}
				}
			}

			close(fd);
		}

		_ukbd_keymapdata.layout = _get_keymap_by_name(keymap);
	}

	if (_ukbd_keymapdata.layout == KB_NONE) {
		switch (CONF_GetLanguage()) {
		case CONF_LANG_GERMAN:
			_ukbd_keymapdata.layout = KB_DE;
			break;

		case CONF_LANG_JAPANESE:
			_ukbd_keymapdata.layout = KB_JP;
			break;

		case CONF_LANG_FRENCH:
			_ukbd_keymapdata.layout = KB_FR;
			break;

		case CONF_LANG_SPANISH:
			_ukbd_keymapdata.layout = KB_ES;
			break;

		case CONF_LANG_ITALIAN:
			_ukbd_keymapdata.layout = KB_IT;
			break;

		case CONF_LANG_DUTCH:
			_ukbd_keymapdata.layout = KB_NL;
			break;

		case CONF_LANG_SIMP_CHINESE:
		case CONF_LANG_TRAD_CHINESE:
		case CONF_LANG_KOREAN:
		default:
			_ukbd_keymapdata.layout = KB_US;
			break;
		}
	}

	if (wskbd_load_keymap(&_ukbd_keymapdata, &_sc_map, &_sc_maplen) < 0) {
		_ukbd_keymapdata.layout = KB_NONE;

		return -4;
	}

	__lwp_queue_init_empty(&_queue);

	if (!_kbd_thread_running) {
		// start the keyboard thread
		_kbd_thread_quit = false;

		memset(_kbd_stack, 0, KBD_THREAD_STACKSIZE);

		s32 res = LWP_CreateThread(&_kbd_thread, _kbd_thread_func, NULL,
									_kbd_stack, KBD_THREAD_STACKSIZE,
									KBD_THREAD_PRIO);

		if (res) {
			USBKeyboard_Close();

			return -6;
		}

		if(keypress_cb)
		{
			_keyBuffer.head = 0;
			_keyBuffer.tail = 0;

			res = LWP_CreateThread(&_kbd_buf_thread, _kbd_buf_thread_func, NULL,
									_kbd_buf_stack, KBD_THREAD_STACKSIZE,
									KBD_THREAD_PRIO);
			if(res) {
				_kbd_thread_quit = true;

				LWP_JoinThread(_kbd_thread, NULL);

				USBKeyboard_Close();
				KEYBOARD_FlushEvents();
				USBKeyboard_Deinitialize();
				_kbd_thread_running = false;
				return -6;
			}

			devoptab_list[STD_IN] = &std_in;
			setvbuf(stdin, NULL , _IONBF, 0);
			_readKey_cb = keypress_cb;
		}
		_kbd_thread_running = true;
	}
	return 0;
}