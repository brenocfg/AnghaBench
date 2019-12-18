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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  CONST 129 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  UNSPEC 128 
 int /*<<< orphan*/  UNSPEC_TLS ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XINT (int /*<<< orphan*/ ,int) ; 

int
tls_mentioned_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case CONST:
      return tls_mentioned_p (XEXP (x, 0));

    case UNSPEC:
      if (XINT (x, 1) == UNSPEC_TLS)
	return 1;

    default:
      return 0;
    }
}