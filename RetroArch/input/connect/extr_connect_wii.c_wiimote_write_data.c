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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct connect_wii_wiimote_t {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  WM_CMD_WRITE_DATA ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  swap_if_little32 (int) ; 
 int /*<<< orphan*/  wiimote_is_connected (struct connect_wii_wiimote_t*) ; 
 int /*<<< orphan*/  wiimote_send (struct connect_wii_wiimote_t*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int wiimote_write_data(struct connect_wii_wiimote_t* wm,
      uint32_t addr, uint8_t* data, uint8_t len)
{
   uint8_t buf[21] = {0};		/* the payload is always 23 */
   int32_t *buf32  = (int32_t*)buf;

   if (!wm || !wiimote_is_connected(wm))
      return 0;
   if (!data || !len)
      return 0;

#ifdef WIIMOTE_DBG
   int i           = 0;
   printf("Writing %i bytes to memory location 0x%x...\n", len, addr);
   printf("Write data is: ");
   for (; i < len; ++i)
      printf("%x ", data[i]);
   printf("\n");
#endif

   /* the offset is in big endian */
   *buf32 = swap_if_little32(addr);

   /* length */
   *(uint8_t*)(buf + 4) = len;

   /* data */
   memcpy(buf + 5, data, len);

   wiimote_send(wm, WM_CMD_WRITE_DATA, buf, 21);
   return 1;
}