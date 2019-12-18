#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int event_type; } ;
typedef  TYPE_1__ MMAL_DBG_ENTRY_T ;

/* Variables and functions */
#define  MMAL_DBG_CLOSED 129 
#define  MMAL_DBG_OPENED 128 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 

__attribute__((used)) static void on_openclose(MMAL_DBG_ENTRY_T *entry,
                         char *buf,
                         size_t buflen)
{
   switch (entry->event_type) {
      case MMAL_DBG_OPENED: snprintf(buf,buflen,"opened"); break;
      case MMAL_DBG_CLOSED: snprintf(buf,buflen,"closed"); break;
      default: break;
   }
}