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
typedef  int uint8_t ;
typedef  int mpi_limb_t ;
struct TYPE_5__ {unsigned int nbits; int nlimbs; int* d; scalar_t__ sign; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 unsigned int BYTES_PER_MPI_LIMB ; 
 unsigned int MAX_EXTERN_MPI_BITS ; 
 TYPE_1__* MPI_NULL ; 
 TYPE_1__* mpi_alloc (unsigned int) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,...) ; 

MPI
mpi_read_from_buffer(const void *xbuffer, unsigned *ret_nread)
{
  const uint8_t *buffer = xbuffer;
  int i, j;
  unsigned nbits, nbytes, nlimbs, nread=0;
  mpi_limb_t a;
  MPI val = MPI_NULL;

  if( *ret_nread < 2 )
    goto leave;
  nbits = buffer[0] << 8 | buffer[1];

  if( nbits > MAX_EXTERN_MPI_BITS ) {
    printk("MPI: mpi too large (%u bits)\n", nbits);
    goto leave;
  }
  buffer += 2;
  nread = 2;

  nbytes = (nbits+7) / 8;
  nlimbs = (nbytes+BYTES_PER_MPI_LIMB-1) / BYTES_PER_MPI_LIMB;
  val = mpi_alloc( nlimbs );
  if (!val)
	  return MPI_NULL;
  i = BYTES_PER_MPI_LIMB - nbytes % BYTES_PER_MPI_LIMB;
  i %= BYTES_PER_MPI_LIMB;
  val->nbits = nbits;
  j= val->nlimbs = nlimbs;
  val->sign = 0;
  for( ; j > 0; j-- ) {
    a = 0;
    for(; i < BYTES_PER_MPI_LIMB; i++ ) {
      if( ++nread > *ret_nread ) {
	printk("MPI: mpi larger than buffer nread=%d ret_nread=%d\n", nread, *ret_nread);
	goto leave;
      }
      a <<= 8;
      a |= *buffer++;
    }
    i = 0;
    val->d[j-1] = a;
  }

 leave:
  *ret_nread = nread;
  return val;
}