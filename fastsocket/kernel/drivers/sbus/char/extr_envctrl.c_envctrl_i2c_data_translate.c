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

/* Variables and functions */
#define  ENVCTRL_TRANSLATE_FULL 130 
#define  ENVCTRL_TRANSLATE_NO 129 
#define  ENVCTRL_TRANSLATE_SCALE 128 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static int envctrl_i2c_data_translate(unsigned char data, int translate_type,
				      int scale, char *tbl, char *bufdata)
{
	int len = 0;

	switch (translate_type) {
	case ENVCTRL_TRANSLATE_NO:
		/* No decode necessary. */
		len = 1;
		bufdata[0] = data;
		break;

	case ENVCTRL_TRANSLATE_FULL:
		/* Decode this way: data = table[data]. */
		len = 1;
		bufdata[0] = tbl[data];
		break;

	case ENVCTRL_TRANSLATE_SCALE:
		/* Decode this way: data = table[data]/scale */
		sprintf(bufdata,"%d ", (tbl[data] * 10) / (scale));
		len = strlen(bufdata);
		bufdata[len - 1] = bufdata[len - 2];
		bufdata[len - 2] = '.';
		break;

	default:
		break;
	};

	return len;
}