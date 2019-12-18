#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gz_statep ;
struct TYPE_4__ {int eof; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_ERRNO ; 
 int /*<<< orphan*/  gz_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read (int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  zstrerror () ; 

__attribute__((used)) static int gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have)
{
   int ret;

   *have = 0;
   do {
      ret = read(state->fd, buf + *have, len - *have);
      if (ret <= 0)
         break;
      *have += ret;
   } while (*have < len);
   if (ret < 0) {
      gz_error(state, Z_ERRNO, zstrerror());
      return -1;
   }
   if (ret == 0)
      state->eof = 1;
   return 0;
}