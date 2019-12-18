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
struct TYPE_2__ {int i; int /*<<< orphan*/  bsize; } ;
struct saa7134_buf {TYPE_1__ vb; } ;

/* Variables and functions */
 int saa7134_buffer_pages (int /*<<< orphan*/ ) ; 

int saa7134_buffer_startpage(struct saa7134_buf *buf)
{
	return saa7134_buffer_pages(buf->vb.bsize) * buf->vb.i;
}