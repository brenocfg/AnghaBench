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
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 

__attribute__((used)) static int
opncls_bseek (struct bfd *abfd, file_ptr offset, int whence)
{
  struct opncls *vec = abfd->iostream;
  switch (whence)
    {
    case SEEK_SET: vec->where = offset; break;
    case SEEK_CUR: vec->where += offset; break;
    case SEEK_END: return -1;
    }
  return 0;
}