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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  ENCODING_16BIT_BIG 133 
#define  ENCODING_16BIT_LITTLE 132 
#define  ENCODING_32BIT_BIG 131 
#define  ENCODING_32BIT_LITTLE 130 
#define  ENCODING_7BIT 129 
#define  ENCODING_8BIT 128 
 int EOF ; 
 int encoding ; 
 int encoding_size ; 
 int getc (int /*<<< orphan*/ *) ; 

int
getcharacter(FILE *pfile, long *rt)
{
	int i, c;
	char buf[4];

	for(i = 0; i < encoding_size; i++) {
		c = getc(pfile);
		if (c == EOF)
			return (-1);
		buf[i] = c;
	}

	switch (encoding) {
	case ENCODING_7BIT:
	case ENCODING_8BIT:
		*rt = buf[0];
		break;
	case ENCODING_16BIT_BIG:
		*rt = (buf[0] << 8) | buf[1];
		break;
	case ENCODING_16BIT_LITTLE:
		*rt = buf[0] | (buf[1] << 8);
		break;
	case ENCODING_32BIT_BIG:
		*rt = ((long) buf[0] << 24) | ((long) buf[1] << 16) |
		    ((long) buf[2] << 8) | buf[3];
		break;
	case ENCODING_32BIT_LITTLE:
		*rt = buf[0] | ((long) buf[1] << 8) | ((long) buf[2] << 16) |
		    ((long) buf[3] << 24);
		break;
	default:
		return (-1);
	}

	return (0);
}