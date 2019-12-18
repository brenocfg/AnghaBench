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
struct p9_fcall {size_t offset; int /*<<< orphan*/ * sdata; scalar_t__ size; } ;

/* Variables and functions */
 size_t MIN (scalar_t__,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t pdu_read(struct p9_fcall *pdu, void *data, size_t size)
{
	size_t len = MIN(pdu->size - pdu->offset, size);
	memcpy(data, &pdu->sdata[pdu->offset], len);
	pdu->offset += len;
	return size - len;
}