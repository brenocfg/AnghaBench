#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; int channel; void* type; } ;
typedef  TYPE_1__ stbi__pic_packet ;
typedef  int /*<<< orphan*/  stbi__context ;
typedef  int /*<<< orphan*/  packets ;

/* Variables and functions */
 scalar_t__ stbi__at_eof (int /*<<< orphan*/ *) ; 
 int stbi__get16be (int /*<<< orphan*/ *) ; 
 void* stbi__get8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__pic_is4 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stbi__rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stbi__skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int stbi__pic_info(stbi__context *s, int *x, int *y, int *comp)
{
   int act_comp=0,num_packets=0,chained,dummy;
   stbi__pic_packet packets[10];

   if (!x) x = &dummy;
   if (!y) y = &dummy;
   if (!comp) comp = &dummy;

   if (!stbi__pic_is4(s,"\x53\x80\xF6\x34")) {
      stbi__rewind(s);
      return 0;
   }

   stbi__skip(s, 88);

   *x = stbi__get16be(s);
   *y = stbi__get16be(s);
   if (stbi__at_eof(s)) {
      stbi__rewind( s);
      return 0;
   }
   if ( (*x) != 0 && (1 << 28) / (*x) < (*y)) {
      stbi__rewind( s );
      return 0;
   }

   stbi__skip(s, 8);

   do {
      stbi__pic_packet *packet;

      if (num_packets==sizeof(packets)/sizeof(packets[0]))
         return 0;

      packet = &packets[num_packets++];
      chained = stbi__get8(s);
      packet->size    = stbi__get8(s);
      packet->type    = stbi__get8(s);
      packet->channel = stbi__get8(s);
      act_comp |= packet->channel;

      if (stbi__at_eof(s)) {
          stbi__rewind( s );
          return 0;
      }
      if (packet->size != 8) {
          stbi__rewind( s );
          return 0;
      }
   } while (chained);

   *comp = (act_comp & 0x10 ? 4 : 3);

   return 1;
}