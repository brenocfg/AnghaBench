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
struct TYPE_4__ {int cl; int sign; unsigned long* sig; int /*<<< orphan*/  canonical; int /*<<< orphan*/  signalling; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int HOST_BITS_PER_LONG ; 
 int REAL_EXP (TYPE_1__ const*) ; 
 size_t SIGSZ ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

unsigned int
real_hash (const REAL_VALUE_TYPE *r)
{
  unsigned int h;
  size_t i;

  h = r->cl | (r->sign << 2);
  switch (r->cl)
    {
    case rvc_zero:
    case rvc_inf:
      return h;

    case rvc_normal:
      h |= REAL_EXP (r) << 3;
      break;

    case rvc_nan:
      if (r->signalling)
	h ^= (unsigned int)-1;
      if (r->canonical)
	return h;
      break;

    default:
      gcc_unreachable ();
    }

  if (sizeof(unsigned long) > sizeof(unsigned int))
    for (i = 0; i < SIGSZ; ++i)
      {
	unsigned long s = r->sig[i];
	h ^= s ^ (s >> (HOST_BITS_PER_LONG / 2));
      }
  else
    for (i = 0; i < SIGSZ; ++i)
      h ^= r->sig[i];

  return h;
}