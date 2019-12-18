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
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int virtscsi_queuecommand (int /*<<< orphan*/ ,struct scsi_cmnd*) ; 

__attribute__((used)) static int virtscsi_queue(struct scsi_cmnd *sc, void (*done)(struct scsi_cmnd *))
{
	sc->scsi_done = done;
	return virtscsi_queuecommand(sc->device->host, sc);
}