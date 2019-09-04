#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  avctx; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_request_sample (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_tlog (int /*<<< orphan*/ ,char*,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int h263p_decode_umotion(MpegEncContext * s, int pred)
{
   int code = 0, sign;

   if (get_bits1(&s->gb)) /* Motion difference = 0 */
      return pred;

   code = 2 + get_bits1(&s->gb);

   while (get_bits1(&s->gb))
   {
      code <<= 1;
      code += get_bits1(&s->gb);
      if (code >= 32768) {
          avpriv_request_sample(s->avctx, "Huge DMV");
          return 0xffff;
      }
   }
   sign = code & 1;
   code >>= 1;

   code = (sign) ? (pred - code) : (pred + code);
   ff_tlog(s->avctx,"H.263+ UMV Motion = %d\n", code);
   return code;

}