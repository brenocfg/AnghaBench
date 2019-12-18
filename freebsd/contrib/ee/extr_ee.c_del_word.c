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
struct TYPE_2__ {int line_length; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* curr_line ; 
 unsigned char* d_char ; 
 unsigned char* d_word ; 
 int d_wrd_len ; 
 int /*<<< orphan*/  draw_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int,int) ; 
 int /*<<< orphan*/  formatted ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 unsigned char* point ; 
 int position ; 
 int /*<<< orphan*/  scr_horz ; 
 int /*<<< orphan*/  scr_vert ; 
 int /*<<< orphan*/  text_changes ; 

void 
del_word()			/* delete word in front of cursor	*/
{
	int tposit;
	int difference;
	unsigned char *d_word2;
	unsigned char *d_word3;
	unsigned char tmp_char[3];

	if (d_word != NULL)
		free(d_word);
	d_word = malloc(curr_line->line_length);
	tmp_char[0] = d_char[0];
	tmp_char[1] = d_char[1];
	tmp_char[2] = d_char[2];
	d_word3 = point;
	d_word2 = d_word;
	tposit = position;
	while ((tposit < curr_line->line_length) && 
				((*d_word3 != ' ') && (*d_word3 != '\t')))
	{
		tposit++;
		*d_word2 = *d_word3;
		d_word2++;
		d_word3++;
	}
	while ((tposit < curr_line->line_length) && 
				((*d_word3 == ' ') || (*d_word3 == '\t')))
	{
		tposit++;
		*d_word2 = *d_word3;
		d_word2++;
		d_word3++;
	}
	*d_word2 = '\0';
	d_wrd_len = difference = d_word2 - d_word;
	d_word2 = point;
	while (tposit < curr_line->line_length)
	{
		tposit++;
		*d_word2 = *d_word3;
		d_word2++;
		d_word3++;
	}
	curr_line->line_length -= difference;
	*d_word2 = '\0';
	draw_line(scr_vert, scr_horz,point,position,curr_line->line_length);
	d_char[0] = tmp_char[0];
	d_char[1] = tmp_char[1];
	d_char[2] = tmp_char[2];
	text_changes = TRUE;
	formatted = FALSE;
}