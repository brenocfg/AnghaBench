#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t fileHandle_t ;
struct TYPE_4__ {int /*<<< orphan*/  o; } ;
struct TYPE_5__ {TYPE_1__ file; } ;
struct TYPE_6__ {TYPE_2__ handleFiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 TYPE_3__* fsh ; 

void	FS_Flush( fileHandle_t f ) {
	fflush(fsh[f].handleFiles.file.o);
}