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
struct opncls {int /*<<< orphan*/  where; } ;
struct bfd {struct opncls* iostream; } ;
typedef  int /*<<< orphan*/  file_ptr ;

/* Variables and functions */

__attribute__((used)) static file_ptr
opncls_btell (struct bfd *abfd)
{
  struct opncls *vec = abfd->iostream;
  return vec->where;
}