#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/ * function; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ FLASH_LIGHT_TEMPO ; 
#define  LCD_ESCAPE_CHAR 128 
 size_t LCD_ESCAPE_LEN ; 
 int LCD_FLAG_B ; 
 int LCD_FLAG_C ; 
 int LCD_FLAG_D ; 
 int LCD_FLAG_F ; 
 int LCD_FLAG_L ; 
 int LCD_FLAG_N ; 
 scalar_t__ get_user (char,char const*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  isdigit (char) ; 
 scalar_t__ lcd_addr_x ; 
 int lcd_addr_y ; 
 int /*<<< orphan*/  lcd_backlight (int) ; 
 scalar_t__ lcd_bwidth ; 
 int /*<<< orphan*/  lcd_clear_fast () ; 
 char* lcd_escape ; 
 size_t lcd_escape_len ; 
 int lcd_flags ; 
 int /*<<< orphan*/  lcd_gotoxy () ; 
 int lcd_height ; 
 int /*<<< orphan*/  lcd_init_display () ; 
 int /*<<< orphan*/  lcd_left_shift ; 
 int /*<<< orphan*/  lcd_print (char) ; 
 scalar_t__ lcd_width ; 
 int /*<<< orphan*/  lcd_write_cmd (int) ; 
 int /*<<< orphan*/  lcd_write_data (unsigned char) ; 
 scalar_t__ light_tempo ; 
 TYPE_1__ scan_timer ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static ssize_t lcd_write(struct file *file,
			 const char *buf, size_t count, loff_t *ppos)
{

	const char *tmp = buf;
	char c;

	for (; count-- > 0; (ppos ? (*ppos)++ : 0), ++tmp) {
		if (!in_interrupt() && (((count + 1) & 0x1f) == 0))
			schedule();	/* let's be a little nice with other processes that need some CPU */

		if (ppos == NULL && file == NULL)
			c = *tmp;	/* let's not use get_user() from the kernel ! */
		else if (get_user(c, tmp))
			return -EFAULT;

		/* first, we'll test if we're in escape mode */
		if ((c != '\n') && lcd_escape_len >= 0) {	/* yes, let's add this char to the buffer */
			lcd_escape[lcd_escape_len++] = c;
			lcd_escape[lcd_escape_len] = 0;
		} else {
			lcd_escape_len = -1;	/* aborts any previous escape sequence */

			switch (c) {
			case LCD_ESCAPE_CHAR:	/* start of an escape sequence */
				lcd_escape_len = 0;
				lcd_escape[lcd_escape_len] = 0;
				break;
			case '\b':	/* go back one char and clear it */
				if (lcd_addr_x > 0) {
					if (lcd_addr_x < lcd_bwidth)	/* check if we're not at the end of the line */
						lcd_write_cmd(0x10);	/* back one char */
					lcd_addr_x--;
				}
				lcd_write_data(' ');	/* replace with a space */
				lcd_write_cmd(0x10);	/* back one char again */
				break;
			case '\014':	/* quickly clear the display */
				lcd_clear_fast();
				break;
			case '\n':	/* flush the remainder of the current line and go to the
					   beginning of the next line */
				for (; lcd_addr_x < lcd_bwidth; lcd_addr_x++)
					lcd_write_data(' ');
				lcd_addr_x = 0;
				lcd_addr_y = (lcd_addr_y + 1) % lcd_height;
				lcd_gotoxy();
				break;
			case '\r':	/* go to the beginning of the same line */
				lcd_addr_x = 0;
				lcd_gotoxy();
				break;
			case '\t':	/* print a space instead of the tab */
				lcd_print(' ');
				break;
			default:	/* simply print this char */
				lcd_print(c);
				break;
			}
		}

		/* now we'll see if we're in an escape mode and if the current
		   escape sequence can be understood.
		 */
		if (lcd_escape_len >= 2) {	/* minimal length for an escape command */
			int processed = 0;	/* 1 means the command has been processed */

			if (!strcmp(lcd_escape, "[2J")) {	/* Clear the display */
				lcd_clear_fast();	/* clear display */
				processed = 1;
			} else if (!strcmp(lcd_escape, "[H")) {	/* Cursor to home */
				lcd_addr_x = lcd_addr_y = 0;
				lcd_gotoxy();
				processed = 1;
			}
			/* codes starting with ^[[L */
			else if ((lcd_escape_len >= 3) &&
				 (lcd_escape[0] == '[') && (lcd_escape[1] == 'L')) {	/* LCD special codes */

				char *esc = lcd_escape + 2;
				int oldflags = lcd_flags;

				/* check for display mode flags */
				switch (*esc) {
				case 'D':	/* Display ON */
					lcd_flags |= LCD_FLAG_D;
					processed = 1;
					break;
				case 'd':	/* Display OFF */
					lcd_flags &= ~LCD_FLAG_D;
					processed = 1;
					break;
				case 'C':	/* Cursor ON */
					lcd_flags |= LCD_FLAG_C;
					processed = 1;
					break;
				case 'c':	/* Cursor OFF */
					lcd_flags &= ~LCD_FLAG_C;
					processed = 1;
					break;
				case 'B':	/* Blink ON */
					lcd_flags |= LCD_FLAG_B;
					processed = 1;
					break;
				case 'b':	/* Blink OFF */
					lcd_flags &= ~LCD_FLAG_B;
					processed = 1;
					break;
				case '+':	/* Back light ON */
					lcd_flags |= LCD_FLAG_L;
					processed = 1;
					break;
				case '-':	/* Back light OFF */
					lcd_flags &= ~LCD_FLAG_L;
					processed = 1;
					break;
				case '*':	/* flash back light using the keypad timer */
					if (scan_timer.function != NULL) {
						if (light_tempo == 0
						    && ((lcd_flags & LCD_FLAG_L)
							== 0))
							lcd_backlight(1);
						light_tempo = FLASH_LIGHT_TEMPO;
					}
					processed = 1;
					break;
				case 'f':	/* Small Font */
					lcd_flags &= ~LCD_FLAG_F;
					processed = 1;
					break;
				case 'F':	/* Large Font */
					lcd_flags |= LCD_FLAG_F;
					processed = 1;
					break;
				case 'n':	/* One Line */
					lcd_flags &= ~LCD_FLAG_N;
					processed = 1;
					break;
				case 'N':	/* Two Lines */
					lcd_flags |= LCD_FLAG_N;
					break;

				case 'l':	/* Shift Cursor Left */
					if (lcd_addr_x > 0) {
						if (lcd_addr_x < lcd_bwidth)
							lcd_write_cmd(0x10);	/* back one char if not at end of line */
						lcd_addr_x--;
					}
					processed = 1;
					break;

				case 'r':	/* shift cursor right */
					if (lcd_addr_x < lcd_width) {
						if (lcd_addr_x < (lcd_bwidth - 1))
							lcd_write_cmd(0x14);	/* allow the cursor to pass the end of the line */
						lcd_addr_x++;
					}
					processed = 1;
					break;

				case 'L':	/* shift display left */
					lcd_left_shift++;
					lcd_write_cmd(0x18);
					processed = 1;
					break;

				case 'R':	/* shift display right */
					lcd_left_shift--;
					lcd_write_cmd(0x1C);
					processed = 1;
					break;

				case 'k':{	/* kill end of line */
						int x;
						for (x = lcd_addr_x; x < lcd_bwidth; x++)
							lcd_write_data(' ');
						lcd_gotoxy();	/* restore cursor position */
						processed = 1;
						break;
					}
				case 'I':	/* reinitialize display */
					lcd_init_display();
					lcd_left_shift = 0;
					processed = 1;
					break;

				case 'G':	/* Generator : LGcxxxxx...xx; */  {
						/* must have <c> between '0' and '7', representing the numerical
						 * ASCII code of the redefined character, and <xx...xx> a sequence
						 * of 16 hex digits representing 8 bytes for each character. Most
						 * LCDs will only use 5 lower bits of the 7 first bytes.
						 */

						unsigned char cgbytes[8];
						unsigned char cgaddr;
						int cgoffset;
						int shift;
						char value;
						int addr;

						if (strchr(esc, ';') == NULL)
							break;

						esc++;

						cgaddr = *(esc++) - '0';
						if (cgaddr > 7) {
							processed = 1;
							break;
						}

						cgoffset = 0;
						shift = 0;
						value = 0;
						while (*esc && cgoffset < 8) {
							shift ^= 4;
							if (*esc >= '0' && *esc <= '9')
								value |= (*esc - '0') << shift;
							else if (*esc >= 'A' && *esc <= 'Z')
								value |= (*esc - 'A' + 10) << shift;
							else if (*esc >= 'a' && *esc <= 'z')
								value |= (*esc - 'a' + 10) << shift;
							else {
								esc++;
								continue;
							}

							if (shift == 0) {
								cgbytes[cgoffset++] = value;
								value = 0;
							}

							esc++;
						}

						lcd_write_cmd(0x40 | (cgaddr * 8));
						for (addr = 0; addr < cgoffset; addr++)
							lcd_write_data(cgbytes[addr]);

						lcd_gotoxy();	/* ensures that we stop writing to CGRAM */
						processed = 1;
						break;
					}
				case 'x':	/* gotoxy : LxXXX[yYYY]; */
				case 'y':	/* gotoxy : LyYYY[xXXX]; */
					if (strchr(esc, ';') == NULL)
						break;

					while (*esc) {
						if (*esc == 'x') {
							esc++;
							lcd_addr_x = 0;
							while (isdigit(*esc)) {
								lcd_addr_x =
								    lcd_addr_x *
								    10 + (*esc -
									  '0');
								esc++;
							}
						} else if (*esc == 'y') {
							esc++;
							lcd_addr_y = 0;
							while (isdigit(*esc)) {
								lcd_addr_y =
								    lcd_addr_y *
								    10 + (*esc -
									  '0');
								esc++;
							}
						} else
							break;
					}

					lcd_gotoxy();
					processed = 1;
					break;
				}	/* end of switch */

				/* Check wether one flag was changed */
				if (oldflags != lcd_flags) {
					/* check wether one of B,C,D flags was changed */
					if ((oldflags ^ lcd_flags) &
					    (LCD_FLAG_B | LCD_FLAG_C | LCD_FLAG_D))
						/* set display mode */
						lcd_write_cmd(0x08 |
							      ((lcd_flags & LCD_FLAG_D) ? 4 : 0) |
							      ((lcd_flags & LCD_FLAG_C) ? 2 : 0) |
							      ((lcd_flags & LCD_FLAG_B) ? 1 : 0));
					/* check wether one of F,N flags was changed */
					else if ((oldflags ^ lcd_flags) &
						 (LCD_FLAG_F | LCD_FLAG_N))
						lcd_write_cmd(0x30 |
							      ((lcd_flags & LCD_FLAG_F) ? 4 : 0) |
							      ((lcd_flags & LCD_FLAG_N) ? 8 : 0));
					/* check wether L flag was changed */
					else if ((oldflags ^ lcd_flags) &
						 (LCD_FLAG_L)) {
						if (lcd_flags & (LCD_FLAG_L))
							lcd_backlight(1);
						else if (light_tempo == 0)	/* switch off the light only when the tempo lighting is gone */
							lcd_backlight(0);
					}
				}
			}

			/* LCD special escape codes */
			/* flush the escape sequence if it's been processed or if it is
			   getting too long. */
			if (processed || (lcd_escape_len >= LCD_ESCAPE_LEN))
				lcd_escape_len = -1;
		}		/* escape codes */
	}

	return tmp - buf;
}