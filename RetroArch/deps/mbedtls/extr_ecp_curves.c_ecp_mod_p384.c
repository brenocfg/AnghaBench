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

__attribute__((used)) static int ecp_mod_p384( mbedtls_mpi *N )
{
    INIT( 384 );

    ADD( 12 ); ADD( 21 ); ADD( 20 );
    SUB( 23 );                                              NEXT; /* A0 */

    ADD( 13 ); ADD( 22 ); ADD( 23 );
    SUB( 12 ); SUB( 20 );                                   NEXT; /* A2 */

    ADD( 14 ); ADD( 23 );
    SUB( 13 ); SUB( 21 );                                   NEXT; /* A2 */

    ADD( 15 ); ADD( 12 ); ADD( 20 ); ADD( 21 );
    SUB( 14 ); SUB( 22 ); SUB( 23 );                        NEXT; /* A3 */

    ADD( 21 ); ADD( 21 ); ADD( 16 ); ADD( 13 ); ADD( 12 ); ADD( 20 ); ADD( 22 );
    SUB( 15 ); SUB( 23 ); SUB( 23 );                        NEXT; /* A4 */

    ADD( 22 ); ADD( 22 ); ADD( 17 ); ADD( 14 ); ADD( 13 ); ADD( 21 ); ADD( 23 );
    SUB( 16 );                                              NEXT; /* A5 */

    ADD( 23 ); ADD( 23 ); ADD( 18 ); ADD( 15 ); ADD( 14 ); ADD( 22 );
    SUB( 17 );                                              NEXT; /* A6 */

    ADD( 19 ); ADD( 16 ); ADD( 15 ); ADD( 23 );
    SUB( 18 );                                              NEXT; /* A7 */

    ADD( 20 ); ADD( 17 ); ADD( 16 );
    SUB( 19 );                                              NEXT; /* A8 */

    ADD( 21 ); ADD( 18 ); ADD( 17 );
    SUB( 20 );                                              NEXT; /* A9 */

    ADD( 22 ); ADD( 19 ); ADD( 18 );
    SUB( 21 );                                              NEXT; /* A10 */

    ADD( 23 ); ADD( 20 ); ADD( 19 );
    SUB( 22 );                                              LAST; /* A11 */

cleanup:
    return( ret );
}