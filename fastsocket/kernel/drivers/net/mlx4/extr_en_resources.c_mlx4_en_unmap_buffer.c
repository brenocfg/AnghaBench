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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct mlx4_buf {int nbufs; TYPE_1__ direct; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  vunmap (int /*<<< orphan*/ ) ; 

void mlx4_en_unmap_buffer(struct mlx4_buf *buf)
{
	if (BITS_PER_LONG == 64 || buf->nbufs == 1)
		return;

	vunmap(buf->direct.buf);
}