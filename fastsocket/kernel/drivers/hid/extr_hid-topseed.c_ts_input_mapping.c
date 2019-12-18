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
 int HID_USAGE ; 
 int HID_USAGE_PAGE ; 
 int /*<<< orphan*/  KEY_ANGLE ; 
 int /*<<< orphan*/  KEY_AUDIO ; 
 int /*<<< orphan*/  KEY_BLUE ; 
 int /*<<< orphan*/  KEY_CHANNEL ; 
 int /*<<< orphan*/  KEY_GREEN ; 
 int /*<<< orphan*/  KEY_HOME ; 
 int /*<<< orphan*/  KEY_LANGUAGE ; 
 int /*<<< orphan*/  KEY_MENU ; 
 int /*<<< orphan*/  KEY_RED ; 
 int /*<<< orphan*/  KEY_SUBTITLE ; 
 int /*<<< orphan*/  KEY_TEXT ; 
 int /*<<< orphan*/  KEY_TV ; 
 int /*<<< orphan*/  KEY_YELLOW ; 
 int /*<<< orphan*/  ts_map_key_clear (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	if ((usage->hid & HID_USAGE_PAGE) != 0x0ffbc0000)
		return 0;

	switch (usage->hid & HID_USAGE) {
        case 0x00d: ts_map_key_clear(KEY_HOME);           break;
        case 0x024: ts_map_key_clear(KEY_MENU);           break;
        case 0x025: ts_map_key_clear(KEY_TV);             break;
        case 0x048: ts_map_key_clear(KEY_RED);            break;
        case 0x047: ts_map_key_clear(KEY_GREEN);          break;
        case 0x049: ts_map_key_clear(KEY_YELLOW);         break;
        case 0x04a: ts_map_key_clear(KEY_BLUE);           break;
        case 0x04b: ts_map_key_clear(KEY_ANGLE);          break;
        case 0x04c: ts_map_key_clear(KEY_LANGUAGE);       break;
        case 0x04d: ts_map_key_clear(KEY_SUBTITLE);       break;
        case 0x031: ts_map_key_clear(KEY_AUDIO);          break;
        case 0x032: ts_map_key_clear(KEY_TEXT);           break;
        case 0x033: ts_map_key_clear(KEY_CHANNEL);        break;
	default:
		return 0;
	}

	return 1;
}