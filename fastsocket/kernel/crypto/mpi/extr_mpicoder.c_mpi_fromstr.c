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
typedef  int mpi_limb_t ;
struct TYPE_5__ {unsigned int alloced; int nlimbs; int sign; int* d; } ;
typedef  TYPE_1__* MPI ;

/* Variables and functions */
 unsigned int BYTES_PER_MPI_LIMB ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mpi_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  mpi_resize (TYPE_1__*,unsigned int) ; 
 int strlen (char const*) ; 

int
mpi_fromstr(MPI val, const char *str)
{
    int hexmode=0, sign=0, prepend_zero=0, i, j, c, c1, c2;
    unsigned nbits, nbytes, nlimbs;
    mpi_limb_t a;

    if( *str == '-' ) {
	sign = 1;
	str++;
    }
    if( *str == '0' && str[1] == 'x' )
	hexmode = 1;
    else
	return -EINVAL; /* other bases are not yet supported */
    str += 2;

    nbits = strlen(str)*4;
    if( nbits % 8 )
	prepend_zero = 1;
    nbytes = (nbits+7) / 8;
    nlimbs = (nbytes+BYTES_PER_MPI_LIMB-1) / BYTES_PER_MPI_LIMB;
    if( val->alloced < nlimbs )
	    if (!mpi_resize(val, nlimbs ))
		    return -ENOMEM;
    i = BYTES_PER_MPI_LIMB - nbytes % BYTES_PER_MPI_LIMB;
    i %= BYTES_PER_MPI_LIMB;
    j= val->nlimbs = nlimbs;
    val->sign = sign;
    for( ; j > 0; j-- ) {
	a = 0;
	for(; i < BYTES_PER_MPI_LIMB; i++ ) {
	    if( prepend_zero ) {
		c1 = '0';
		prepend_zero = 0;
	    }
	    else
		c1 = *str++;
	    assert(c1);
	    c2 = *str++;
	    assert(c2);
	    if( c1 >= '0' && c1 <= '9' )
		c = c1 - '0';
	    else if( c1 >= 'a' && c1 <= 'f' )
		c = c1 - 'a' + 10;
	    else if( c1 >= 'A' && c1 <= 'F' )
		c = c1 - 'A' + 10;
	    else {
		mpi_clear(val);
		return 1;
	    }
	    c <<= 4;
	    if( c2 >= '0' && c2 <= '9' )
		c |= c2 - '0';
	    else if( c2 >= 'a' && c2 <= 'f' )
		c |= c2 - 'a' + 10;
	    else if( c2 >= 'A' && c2 <= 'F' )
		c |= c2 - 'A' + 10;
	    else {
		mpi_clear(val);
		return 1;
	    }
	    a <<= 8;
	    a |= c;
	}
	i = 0;

	val->d[j-1] = a;
    }

    return 0;
}