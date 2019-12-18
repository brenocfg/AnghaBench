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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ int32 ;

/* Variables and functions */
 int /*<<< orphan*/  FCEUI_CRC32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  en32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  magic ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outcounter ; 

__attribute__((used)) static uint8 *MakeUDP(uint8 *data, int32 len)
{
 /* UDP packet data header is 12 bytes in length. */
 static uint8 buf[12+32]; // arbitrary 32.
 
 en32(buf+4,magic);
 en32(buf+8,outcounter);
 memcpy(buf+12,data,len);
 en32(buf,FCEUI_CRC32(0,buf+4,8+len));
 return(buf);
}