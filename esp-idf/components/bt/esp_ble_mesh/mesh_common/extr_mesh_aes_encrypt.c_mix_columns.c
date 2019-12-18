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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  t ;

/* Variables and functions */
 int Nb ; 
 int Nk ; 
 int /*<<< orphan*/  _copy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mult_row_column (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mix_columns(uint8_t *s)
{
    uint8_t t[Nb * Nk];

    mult_row_column(t, s);
    mult_row_column(&t[Nb], s + Nb);
    mult_row_column(&t[2 * Nb], s + (2 * Nb));
    mult_row_column(&t[3 * Nb], s + (3 * Nb));
    (void) _copy(s, sizeof(t), t, sizeof(t));
}