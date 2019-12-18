#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; } ;
struct TYPE_6__ {TYPE_1__ bulk; } ;
struct TYPE_7__ {scalar_t__ event_type; TYPE_2__ u; } ;
typedef  TYPE_3__ MMAL_DBG_ENTRY_T ;

/* Variables and functions */
 scalar_t__ MMAL_DBG_BULK_TX ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,int) ; 

__attribute__((used)) static void on_bulk(MMAL_DBG_ENTRY_T *entry,
                    char *buf,
                    size_t buflen)
{
   const char *name = entry->event_type == MMAL_DBG_BULK_TX ? "tx" : "rx";
   snprintf(buf,buflen,"bulk %s len %d", name, entry->u.bulk.len);
}