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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 size_t fwrite (char const*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror_fatal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ck_fwrite (char const *buf, size_t size, FILE *f)
{
  if (fwrite (buf, sizeof (char), size, f) != size)
    perror_fatal (_("write failed"));
}