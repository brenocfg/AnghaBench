#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int bi_valid; int bi_buf; } ;
typedef  TYPE_1__ deflate_state ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  put_byte (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_short (TYPE_1__*,int) ; 

__attribute__((used)) static void bi_flush(deflate_state *s)
   {
      if (s->bi_valid == 16) {
         put_short(s, s->bi_buf);
         s->bi_buf = 0;
         s->bi_valid = 0;
      } else if (s->bi_valid >= 8) {
         put_byte(s, (Byte)s->bi_buf);
         s->bi_buf >>= 8;
         s->bi_valid -= 8;
      }
   }