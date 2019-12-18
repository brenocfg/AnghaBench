#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct mlx4_mtt {int dummy; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_3__ {scalar_t__ map; } ;
struct mlx4_buf {int npages; int nbufs; int page_shift; TYPE_2__* page_list; TYPE_1__ direct; } ;
struct TYPE_4__ {scalar_t__ map; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mlx4_write_mtt (struct mlx4_dev*,struct mlx4_mtt*,int /*<<< orphan*/ ,int,scalar_t__*) ; 

int mlx4_buf_write_mtt(struct mlx4_dev *dev, struct mlx4_mtt *mtt,
		       struct mlx4_buf *buf)
{
	u64 *page_list;
	int err;
	int i;

	page_list = kmalloc(buf->npages * sizeof *page_list, GFP_KERNEL);
	if (!page_list)
		return -ENOMEM;

	for (i = 0; i < buf->npages; ++i)
		if (buf->nbufs == 1)
			page_list[i] = buf->direct.map + (i << buf->page_shift);
		else
			page_list[i] = buf->page_list[i].map;

	err = mlx4_write_mtt(dev, mtt, 0, buf->npages, page_list);

	kfree(page_list);
	return err;
}