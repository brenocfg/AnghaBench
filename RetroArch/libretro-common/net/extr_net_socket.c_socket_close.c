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

/* Variables and functions */
 int close (int) ; 
 int closesocket (int) ; 
 int sceNetSocketClose (int) ; 
 int socketclose (int) ; 

int socket_close(int fd)
{
#if defined(_WIN32) && !defined(_XBOX360)
   /* WinSock has headers from the stone age. */
   return closesocket(fd);
#elif defined(__CELLOS_LV2__) || defined(WIIU)
   return socketclose(fd);
#elif defined(VITA)
   return sceNetSocketClose(fd);
#else
   return close(fd);
#endif
}