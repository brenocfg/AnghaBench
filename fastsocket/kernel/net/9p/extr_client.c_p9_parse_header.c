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
struct p9_fcall {int offset; int size; int /*<<< orphan*/  tag; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  P9_DEBUG_9P ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int p9pdu_readf (struct p9_fcall*,int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
p9_parse_header(struct p9_fcall *pdu, int32_t *size, int8_t *type, int16_t *tag,
								int rewind)
{
	int8_t r_type;
	int16_t r_tag;
	int32_t r_size;
	int offset = pdu->offset;
	int err;

	pdu->offset = 0;
	if (pdu->size == 0)
		pdu->size = 7;

	err = p9pdu_readf(pdu, 0, "dbw", &r_size, &r_type, &r_tag);
	if (err)
		goto rewind_and_exit;

	pdu->size = r_size;
	pdu->id = r_type;
	pdu->tag = r_tag;

	P9_DPRINTK(P9_DEBUG_9P, "<<< size=%d type: %d tag: %d\n", pdu->size,
							pdu->id, pdu->tag);

	if (type)
		*type = r_type;
	if (tag)
		*tag = r_tag;
	if (size)
		*size = r_size;


rewind_and_exit:
	if (rewind)
		pdu->offset = offset;
	return err;
}