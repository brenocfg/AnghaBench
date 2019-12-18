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
typedef  unsigned long bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_put_16 (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_64 (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_8 (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
put_value (bfd_vma        size,
	   unsigned long  chunksz,
	   bfd *          input_bfd,
	   bfd_vma        x,
	   bfd_byte *     location)
{
  location += (size - chunksz);

  for (; size; size -= chunksz, location -= chunksz, x >>= (chunksz * 8)) 
    {
      switch (chunksz)
	{
	default:
	case 0:
	  abort ();
	case 1:
	  bfd_put_8 (input_bfd, x, location);
	  break;
	case 2:
	  bfd_put_16 (input_bfd, x, location);
	  break;
	case 4:
	  bfd_put_32 (input_bfd, x, location);
	  break;
	case 8:
#ifdef BFD64
	  bfd_put_64 (input_bfd, x, location);
#else
	  abort ();
#endif
	  break;
	}
    }
}