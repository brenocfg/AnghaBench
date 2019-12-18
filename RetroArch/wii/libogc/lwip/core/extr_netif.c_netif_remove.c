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
struct netif {struct netif* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETIF_DEBUG ; 
 struct netif* netif_default ; 
 struct netif* netif_list ; 

void netif_remove(struct netif * netif)
{
  if ( netif == NULL ) return;

  /*  is it the first netif? */
  if (netif_list == netif) {
    netif_list = netif->next;
  }
  else {
    /*  look for netif further down the list */
    struct netif * tmpNetif;
    for (tmpNetif = netif_list; tmpNetif != NULL; tmpNetif = tmpNetif->next) {
      if (tmpNetif->next == netif) {
        tmpNetif->next = netif->next;
        break;
        }
    }
    if (tmpNetif == NULL)
      return; /*  we didn't find any netif today */
  }
  /* this netif is default? */
  if (netif_default == netif)
    /* reset default netif */
    netif_default = NULL;
  LWIP_DEBUGF( NETIF_DEBUG, ("netif_remove: removed netif\n") );
}