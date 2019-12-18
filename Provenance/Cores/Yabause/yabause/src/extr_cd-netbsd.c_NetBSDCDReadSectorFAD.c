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
typedef  int u32 ;
typedef  int /*<<< orphan*/  syncHdr ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int hCDROM ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int const*,int) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 

__attribute__((used)) static int NetBSDCDReadSectorFAD(u32 FAD, void *buffer) {
       static const s8 syncHdr[] = {
           0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
           0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00 };

       if (hCDROM != -1)
       {
               memcpy(buffer, syncHdr, sizeof (syncHdr));
               lseek(hCDROM, (FAD - 150) * 2048, SEEK_SET);
               read(hCDROM, (char *)buffer + 0x10, 2048);

               return 1;
       }

       return 0;
}