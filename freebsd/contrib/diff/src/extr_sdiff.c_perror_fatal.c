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

/* Variables and functions */
 int /*<<< orphan*/  checksigs () ; 
 int errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  exiterr () ; 

__attribute__((used)) static void
perror_fatal (char const *msg)
{
  int e = errno;
  checksigs ();
  error (0, e, "%s", msg);
  exiterr ();
}