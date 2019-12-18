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
typedef  int /*<<< orphan*/  mbedtls_mpi ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (int) ; 
 int /*<<< orphan*/  INIT (int) ; 
 int /*<<< orphan*/  LAST ; 
 int /*<<< orphan*/  NEXT ; 
 int /*<<< orphan*/  SUB (int) ; 
 int ret ; 

__attribute__((used)) static int ecp_mod_p224( mbedtls_mpi *N )
{
    INIT( 224 );

    SUB(  7 ); SUB( 11 );               NEXT; /* A0 += -A7 - A11 */
    SUB(  8 ); SUB( 12 );               NEXT; /* A1 += -A8 - A12 */
    SUB(  9 ); SUB( 13 );               NEXT; /* A2 += -A9 - A13 */
    SUB( 10 ); ADD(  7 ); ADD( 11 );    NEXT; /* A3 += -A10 + A7 + A11 */
    SUB( 11 ); ADD(  8 ); ADD( 12 );    NEXT; /* A4 += -A11 + A8 + A12 */
    SUB( 12 ); ADD(  9 ); ADD( 13 );    NEXT; /* A5 += -A12 + A9 + A13 */
    SUB( 13 ); ADD( 10 );               LAST; /* A6 += -A13 + A10 */

cleanup:
    return( ret );
}