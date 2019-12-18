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

/* Variables and functions */
 int /*<<< orphan*/  EL_UIO ; 
 int /*<<< orphan*/  SekPc ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int prot_lk3_cmd ; 
 int prot_lk3_data ; 

__attribute__((used)) static u32 PicoRead8_plk3(u32 a)
{
  u32 d = 0;
  switch (prot_lk3_cmd) {
    case 1: d = prot_lk3_data >> 1; break;
    case 2: // nibble rotate
      d = ((prot_lk3_data >> 4) | (prot_lk3_data << 4)) & 0xff;
      break;
    case 3: // bit rotate
      d = prot_lk3_data;
      d = (d >> 4) | (d << 4);
      d = ((d & 0xcc) >> 2) | ((d & 0x33) << 2);
      d = ((d & 0xaa) >> 1) | ((d & 0x55) << 1);
      break;
/* Top Fighter 2000 MK VIII (Unl)
      case 0x98: d = 0x50; break; // prot_lk3_data == a8 here
      case 0x67: d = 0xde; break; // prot_lk3_data == 7b here (rot!)
      case 0xb5: d = 0x9f; break; // prot_lk3_data == 4a
*/
    default:
      elprintf(EL_UIO, "unhandled prot cmd %02x @%06x", prot_lk3_cmd, SekPc);
      break;
  }

  elprintf(EL_UIO, "prot r8  [%06x]   %02x @%06x", a, d, SekPc);
  return d;
}