#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int disco_number; size_t disco_index; TYPE_2__* discoveries; } ;
typedef  TYPE_1__ irnet_socket ;
struct TYPE_7__ {int daddr; char* info; int saddr; int* hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_INFO ; 
 int /*<<< orphan*/  CTRL_TRACE ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DENTER (int /*<<< orphan*/ ,char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  irnet_get_discovery_log (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*,int,int,int) ; 

__attribute__((used)) static inline int
irnet_read_discovery_log(irnet_socket *	ap,
			 char *		event)
{
  int		done_event = 0;

  DENTER(CTRL_TRACE, "(ap=0x%p, event=0x%p)\n",
	 ap, event);

  /* Test if we have some work to do or we have already finished */
  if(ap->disco_number == -1)
    {
      DEBUG(CTRL_INFO, "Already done\n");
      return 0;
    }

  /* Test if it's the first time and therefore we need to get the log */
  if(ap->discoveries == NULL)
    irnet_get_discovery_log(ap);

  /* Check if we have more item to dump */
  if(ap->disco_index < ap->disco_number)
    {
      /* Write an event */
      sprintf(event, "Found %08x (%s) behind %08x {hints %02X-%02X}\n",
	      ap->discoveries[ap->disco_index].daddr,
	      ap->discoveries[ap->disco_index].info,
	      ap->discoveries[ap->disco_index].saddr,
	      ap->discoveries[ap->disco_index].hints[0],
	      ap->discoveries[ap->disco_index].hints[1]);
      DEBUG(CTRL_INFO, "Writing discovery %d : %s\n",
	    ap->disco_index, ap->discoveries[ap->disco_index].info);

      /* We have an event */
      done_event = 1;
      /* Next discovery */
      ap->disco_index++;
    }

  /* Check if we have done the last item */
  if(ap->disco_index >= ap->disco_number)
    {
      /* No more items : remove the log and signal termination */
      DEBUG(CTRL_INFO, "Cleaning up log (0x%p)\n",
	    ap->discoveries);
      if(ap->discoveries != NULL)
	{
	  /* Cleanup our copy of the discovery log */
	  kfree(ap->discoveries);
	  ap->discoveries = NULL;
	}
      ap->disco_number = -1;
    }

  return done_event;
}