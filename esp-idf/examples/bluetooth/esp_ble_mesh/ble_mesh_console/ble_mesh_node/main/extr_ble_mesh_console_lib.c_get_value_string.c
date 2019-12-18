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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int hexstr_2_bin (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int get_value_string(char *value_in, char *buf)
{
    int result = -1;

    uint16_t length = strlen(value_in);
    for(int i = 0; i<length; i++) {
        printf("%c", value_in[i]);
    }

    if (length > 2) {
        if (value_in[0] == '0' && value_in[1] == 'x') {
            buf[(length - 2) / 2] = 0;
            result = hexstr_2_bin(&value_in[2], (uint8_t *)buf, (length - 2) / 2);
            length = (length - 2) / 2;
        } else {
            strcpy(buf, value_in);
            result = 0;
        }
    } else {
        strcpy(buf, value_in);
        result = 0;
    }

    return result;
}