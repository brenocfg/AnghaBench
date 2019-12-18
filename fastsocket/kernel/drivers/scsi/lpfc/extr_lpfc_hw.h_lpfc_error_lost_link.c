#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* ulpWord; } ;
struct TYPE_5__ {scalar_t__ ulpStatus; TYPE_1__ un; } ;
typedef  TYPE_2__ IOCB_t ;

/* Variables and functions */
 scalar_t__ IOERR_LINK_DOWN ; 
 scalar_t__ IOERR_SLI_ABORTED ; 
 scalar_t__ IOERR_SLI_DOWN ; 
 scalar_t__ IOSTAT_LOCAL_REJECT ; 

__attribute__((used)) static inline int
lpfc_error_lost_link(IOCB_t *iocbp)
{
	return (iocbp->ulpStatus == IOSTAT_LOCAL_REJECT &&
		(iocbp->un.ulpWord[4] == IOERR_SLI_ABORTED ||
		 iocbp->un.ulpWord[4] == IOERR_LINK_DOWN ||
		 iocbp->un.ulpWord[4] == IOERR_SLI_DOWN));
}