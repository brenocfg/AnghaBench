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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ int32 ;

/* Variables and functions */
 scalar_t__ FCEUI_CRC32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ de32 (int /*<<< orphan*/ *) ; 
 scalar_t__ incounter ; 
 scalar_t__ magic ; 

__attribute__((used)) static int CheckUDP(uint8 *packet, int32 len, int32 alt)
{
 uint32 crc;
 uint32 repcrc;

 crc=FCEUI_CRC32(0,packet+4,len+8);
 repcrc=de32(packet);

 if(crc!=repcrc) return(0); /* CRC32 mismatch, bad packet. */
  packet+=4;

 if(de32(packet)!=magic) /* Magic number mismatch, bad or spoofed packet. */
  return(0);

 packet+=4;
 if(alt)
 {
  if(de32(packet)<incounter) /* Time warped packet. */
   return(0);
 }
 else
  if(de32(packet)!=incounter) /* Time warped packet. */
   return(0);
 return(1);
}