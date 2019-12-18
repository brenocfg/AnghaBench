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
struct queue {int /*<<< orphan*/  offset; } ;
struct fs_dev {int dummy; } ;
struct FS_QENTRY {int dummy; } ;

/* Variables and functions */
 int Q_ADDR_MASK ; 
 int /*<<< orphan*/  Q_WP (int /*<<< orphan*/ ) ; 
 struct FS_QENTRY* bus_to_virt (int) ; 
 int read_fs (struct fs_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct FS_QENTRY *get_qentry (struct fs_dev *dev, struct queue *q)
{
	return bus_to_virt (read_fs (dev, Q_WP(q->offset)) & Q_ADDR_MASK);
}