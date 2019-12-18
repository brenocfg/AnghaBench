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
struct UPNPUrls {int dummy; } ;
struct UPNPDev {int /*<<< orphan*/  descURL; struct UPNPDev* pNext; int /*<<< orphan*/  st; } ;
struct IGDdatas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetUPNPUrls (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freeUPNPDevlist (struct UPNPDev*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ miniwget (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parserootdesc (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 
 struct UPNPDev* upnpDiscover (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  urls ; 

void natt_init(void)
{
#ifndef HAVE_SOCKET_LEGACY
#if HAVE_MINIUPNPC
   struct UPNPDev * devlist;
   struct UPNPDev * dev;
   char * descXML;
   int descXMLsize = 0;
   int upnperror = 0;
   memset(&urls, 0, sizeof(struct UPNPUrls));
   memset(&data, 0, sizeof(struct IGDdatas));
   devlist = upnpDiscover(2000, NULL, NULL, 0, 0, 2, &upnperror);
   if (devlist)
   {
      dev = devlist;
      while (dev)
      {
         if (strstr (dev->st, "InternetGatewayDevice"))
            break;
         dev = dev->pNext;
      }
      if (!dev)
         dev = devlist;

      descXML = (char *) miniwget(dev->descURL, &descXMLsize, 0, NULL);
      if (descXML)
      {
         parserootdesc(descXML, descXMLsize, &data);
         free (descXML);
         descXML = 0;
         GetUPNPUrls (&urls, &data, dev->descURL, 0);
      }
      freeUPNPDevlist(devlist);
   }
#endif
#endif
}