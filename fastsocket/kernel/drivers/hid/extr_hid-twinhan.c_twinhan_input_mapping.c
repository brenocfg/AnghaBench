#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hid_usage {int hid; } ;
struct hid_input {int dummy; } ;
struct hid_field {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int HID_UP_KEYBOARD ; 
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_CANCEL ; 
 int /*<<< orphan*/  KEY_CHANNELDOWN ; 
 int /*<<< orphan*/  KEY_CHANNELUP ; 
 int /*<<< orphan*/  KEY_EPG ; 
 int /*<<< orphan*/  KEY_FAVORITES ; 
 int /*<<< orphan*/  KEY_FORWARD ; 
 int /*<<< orphan*/  KEY_LIST ; 
 int /*<<< orphan*/  KEY_MUTE ; 
 int /*<<< orphan*/  KEY_NUMERIC_0 ; 
 int /*<<< orphan*/  KEY_NUMERIC_1 ; 
 int /*<<< orphan*/  KEY_NUMERIC_2 ; 
 int /*<<< orphan*/  KEY_NUMERIC_3 ; 
 int /*<<< orphan*/  KEY_NUMERIC_4 ; 
 int /*<<< orphan*/  KEY_NUMERIC_5 ; 
 int /*<<< orphan*/  KEY_NUMERIC_6 ; 
 int /*<<< orphan*/  KEY_NUMERIC_7 ; 
 int /*<<< orphan*/  KEY_NUMERIC_8 ; 
 int /*<<< orphan*/  KEY_NUMERIC_9 ; 
 int /*<<< orphan*/  KEY_PAUSE ; 
 int /*<<< orphan*/  KEY_PLAY ; 
 int /*<<< orphan*/  KEY_POWER2 ; 
 int /*<<< orphan*/  KEY_PRINT ; 
 int /*<<< orphan*/  KEY_PROGRAM ; 
 int /*<<< orphan*/  KEY_RECORD ; 
 int /*<<< orphan*/  KEY_RESTART ; 
 int /*<<< orphan*/  KEY_REWIND ; 
 int /*<<< orphan*/  KEY_SCREEN ; 
 int /*<<< orphan*/  KEY_STOP ; 
 int /*<<< orphan*/  KEY_TAB ; 
 int /*<<< orphan*/  KEY_TEXT ; 
 int /*<<< orphan*/  KEY_VOLUMEDOWN ; 
 int /*<<< orphan*/  KEY_VOLUMEUP ; 
 int /*<<< orphan*/  th_map_key_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twinhan_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOARD)
		return 0;

	switch (usage->hid & HID_USAGE) {
	/* Map all keys from Twinhan Remote */
	case 0x004: th_map_key_clear(KEY_TEXT);         break;
	case 0x006: th_map_key_clear(KEY_RESTART);      break;
	case 0x008: th_map_key_clear(KEY_EPG);          break;
	case 0x00c: th_map_key_clear(KEY_REWIND);       break;
	case 0x00e: th_map_key_clear(KEY_PROGRAM);      break;
	case 0x00f: th_map_key_clear(KEY_LIST);         break;
	case 0x010: th_map_key_clear(KEY_MUTE);         break;
	case 0x011: th_map_key_clear(KEY_FORWARD);      break;
	case 0x013: th_map_key_clear(KEY_PRINT);        break;
	case 0x017: th_map_key_clear(KEY_PAUSE);        break;
	case 0x019: th_map_key_clear(KEY_FAVORITES);    break;
	case 0x01d: th_map_key_clear(KEY_SCREEN);       break;
	case 0x01e: th_map_key_clear(KEY_NUMERIC_1);    break;
	case 0x01f: th_map_key_clear(KEY_NUMERIC_2);    break;
	case 0x020: th_map_key_clear(KEY_NUMERIC_3);    break;
	case 0x021: th_map_key_clear(KEY_NUMERIC_4);    break;
	case 0x022: th_map_key_clear(KEY_NUMERIC_5);    break;
	case 0x023: th_map_key_clear(KEY_NUMERIC_6);    break;
	case 0x024: th_map_key_clear(KEY_NUMERIC_7);    break;
	case 0x025: th_map_key_clear(KEY_NUMERIC_8);    break;
	case 0x026: th_map_key_clear(KEY_NUMERIC_9);    break;
	case 0x027: th_map_key_clear(KEY_NUMERIC_0);    break;
	case 0x028: th_map_key_clear(KEY_PLAY);         break;
	case 0x029: th_map_key_clear(KEY_CANCEL);       break;
	case 0x02b: th_map_key_clear(KEY_TAB);          break;
	/* Power       = 0x0e0 + 0x0e1 + 0x0e2 + 0x03f */
	case 0x03f: th_map_key_clear(KEY_POWER2);       break;
	case 0x04a: th_map_key_clear(KEY_RECORD);       break;
	case 0x04b: th_map_key_clear(KEY_CHANNELUP);    break;
	case 0x04d: th_map_key_clear(KEY_STOP);         break;
	case 0x04e: th_map_key_clear(KEY_CHANNELDOWN);  break;
	/* Volume down = 0x0e1 + 0x051                 */
	case 0x051: th_map_key_clear(KEY_VOLUMEDOWN);   break;
	/* Volume up   = 0x0e1 + 0x052                 */
	case 0x052: th_map_key_clear(KEY_VOLUMEUP);     break;
	/* Kill the extra keys used for multi-key "power" and "volume" keys
	 * as well as continuously to release CTRL,ALT,META,... keys */
	case 0x0e0:
	case 0x0e1:
	case 0x0e2:
	case 0x0e3:
	case 0x0e4:
	case 0x0e5:
	case 0x0e6:
	case 0x0e7:
	default:
		return -1;
	}
	return 1;
}