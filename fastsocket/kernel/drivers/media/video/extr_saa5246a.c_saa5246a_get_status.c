#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char charset; int delete; int headline; int subtitle; int supp_header; int update; int inter_seq; int dis_disp; int serial; int notfound; int pblf; int hamming; int /*<<< orphan*/  minute; int /*<<< orphan*/  hour; int /*<<< orphan*/  pagenum; } ;
typedef  TYPE_1__ vtx_pageinfo_t ;
struct saa5246a_device {int* is_searching; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_END ; 
 int EINVAL ; 
 int EIO ; 
 unsigned char NUM_DAUS ; 
 int /*<<< orphan*/  R10_CURSER_COLUMN_0 ; 
 unsigned char R8_DO_NOT_CLEAR_MEMORY ; 
 int /*<<< orphan*/  R9_CURSER_ROW_25 ; 
 unsigned char ROW25_COLUMN0_TO_7_HAMMING_ERROR ; 
 unsigned char ROW25_COLUMN3_DELETE_PAGE ; 
 unsigned char ROW25_COLUMN5_INSERT_HEADLINE ; 
 unsigned char ROW25_COLUMN5_INSERT_SUBTITLE ; 
 unsigned char ROW25_COLUMN6_INTERRUPTED_SEQUENCE ; 
 unsigned char ROW25_COLUMN6_SUPPRESS_DISPLAY ; 
 unsigned char ROW25_COLUMN6_SUPPRESS_HEADER ; 
 unsigned char ROW25_COLUMN6_UPDATE_PAGE ; 
 unsigned char ROW25_COLUMN7_CHARACTER_SET ; 
 unsigned char ROW25_COLUMN7_SERIAL_MODE ; 
 unsigned char ROW25_COLUMN8_PAGE_NOT_FOUND ; 
 unsigned char ROW25_COLUMN9_PAGE_BEING_LOOKED_FOR ; 
 int /*<<< orphan*/  SAA5246A_REGISTER_R8 ; 
 scalar_t__ i2c_getdata (struct saa5246a_device*,int,unsigned char*) ; 
 scalar_t__ i2c_senddata (struct saa5246a_device*,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa5246a_extract_hour_from_infobits (unsigned char*) ; 
 int /*<<< orphan*/  saa5246a_extract_minutes_from_infobits (unsigned char*) ; 
 int /*<<< orphan*/  saa5246a_extract_pagenum_from_infobits (unsigned char*) ; 

__attribute__((used)) static inline int saa5246a_get_status(struct saa5246a_device *t,
    vtx_pageinfo_t *info, unsigned char dau_no)
{
	unsigned char infobits[10];
	int column;

	if (dau_no >= NUM_DAUS)
		return -EINVAL;

	if (i2c_senddata(t, SAA5246A_REGISTER_R8,

		dau_no |
		R8_DO_NOT_CLEAR_MEMORY,

		R9_CURSER_ROW_25,

		R10_CURSER_COLUMN_0,

		COMMAND_END) ||
		i2c_getdata(t, 10, infobits))
	{
		return -EIO;
	}

	info->pagenum = saa5246a_extract_pagenum_from_infobits(infobits);
	info->hour    = saa5246a_extract_hour_from_infobits(infobits);
	info->minute  = saa5246a_extract_minutes_from_infobits(infobits);
	info->charset = ((infobits[7] & ROW25_COLUMN7_CHARACTER_SET) >> 1);
	info->delete = !!(infobits[3] & ROW25_COLUMN3_DELETE_PAGE);
	info->headline = !!(infobits[5] & ROW25_COLUMN5_INSERT_HEADLINE);
	info->subtitle = !!(infobits[5] & ROW25_COLUMN5_INSERT_SUBTITLE);
	info->supp_header = !!(infobits[6] & ROW25_COLUMN6_SUPPRESS_HEADER);
	info->update = !!(infobits[6] & ROW25_COLUMN6_UPDATE_PAGE);
	info->inter_seq = !!(infobits[6] & ROW25_COLUMN6_INTERRUPTED_SEQUENCE);
	info->dis_disp = !!(infobits[6] & ROW25_COLUMN6_SUPPRESS_DISPLAY);
	info->serial = !!(infobits[7] & ROW25_COLUMN7_SERIAL_MODE);
	info->notfound = !!(infobits[8] & ROW25_COLUMN8_PAGE_NOT_FOUND);
	info->pblf = !!(infobits[9] & ROW25_COLUMN9_PAGE_BEING_LOOKED_FOR);
	info->hamming = 0;
	for (column = 0; column <= 7; column++) {
		if (infobits[column] & ROW25_COLUMN0_TO_7_HAMMING_ERROR) {
			info->hamming = 1;
			break;
		}
	}
	if (!info->hamming && !info->notfound)
		t->is_searching[dau_no] = false;
	return 0;
}