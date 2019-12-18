#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ide_taskfile {int /*<<< orphan*/  error; } ;
struct TYPE_8__ {TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_7__ {TYPE_1__* tp_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* tf_read ) (TYPE_3__*,struct ide_taskfile*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_VALID_ERROR ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct ide_taskfile*,int /*<<< orphan*/ ) ; 

u8 ide_read_error(ide_drive_t *drive)
{
	struct ide_taskfile tf;

	drive->hwif->tp_ops->tf_read(drive, &tf, IDE_VALID_ERROR);

	return tf.error;
}