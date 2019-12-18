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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct connect_wii_wiimote_t {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  WM_CMD_READ_DATA ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  swap_if_little16 (int) ; 
 int /*<<< orphan*/  swap_if_little32 (int) ; 
 int /*<<< orphan*/  wiimote_is_connected (struct connect_wii_wiimote_t*) ; 
 int /*<<< orphan*/  wiimote_send (struct connect_wii_wiimote_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int wiimote_read_data(struct connect_wii_wiimote_t* wm, uint32_t addr,
      uint16_t len)
{
   uint8_t buf[6] = {0};
   int32_t *buf32 = (int32_t*)buf;
   int16_t *buf16 = (int16_t*)(buf + 4);

   /* No puden ser mas de 16 lo leido o vendra en trozos! */

   if (!wm || !wiimote_is_connected(wm) || !len)
      return 0;

   /* the offsets are in big endian */
   *buf32         = swap_if_little32(addr);
   *buf16         = swap_if_little16(len);

#ifdef WIIMOTE_DBG
   printf("Request read at address: 0x%x  length: %i", addr, len);
#endif
   wiimote_send(wm, WM_CMD_READ_DATA, buf, 6);

   return 1;
}