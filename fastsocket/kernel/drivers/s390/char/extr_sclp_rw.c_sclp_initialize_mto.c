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
struct TYPE_2__ {int length; } ;
struct write_sccb {TYPE_1__ header; } ;
struct sclp_buffer {char* current_line; scalar_t__ current_length; struct write_sccb* sccb; } ;
struct mto {int length; int type; int /*<<< orphan*/  line_type_flags; } ;
typedef  int addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LNTPFLGS_ENDTEXT ; 
 int MAX_SCCB_ROOM ; 
 int /*<<< orphan*/  memset (struct mto*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
sclp_initialize_mto(struct sclp_buffer *buffer, int max_len)
{
	struct write_sccb *sccb;
	struct mto *mto;
	int mto_size;

	/* max size of new Message Text Object including message text  */
	mto_size = sizeof(struct mto) + max_len;

	/* check if current buffer sccb can contain the mto */
	sccb = buffer->sccb;
	if ((MAX_SCCB_ROOM - sccb->header.length) < mto_size)
		return -ENOMEM;

	/* find address of new message text object */
	mto = (struct mto *)(((addr_t) sccb) + sccb->header.length);

	/*
	 * fill the new Message-Text Object,
	 * starting behind the former last byte of the SCCB
	 */
	memset(mto, 0, sizeof(struct mto));
	mto->length = sizeof(struct mto);
	mto->type = 4;	/* message text object */
	mto->line_type_flags = LNTPFLGS_ENDTEXT; /* end text */

	/* set pointer to first byte after struct mto. */
	buffer->current_line = (char *) (mto + 1);
	buffer->current_length = 0;

	return 0;
}