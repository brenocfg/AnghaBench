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

__attribute__((used)) static inline void shift_rows(uint8_t *s)
{
    uint8_t t[Nb * Nk];

    t[0]  = s[0]; t[1] = s[5]; t[2] = s[10]; t[3] = s[15];
    t[4]  = s[4]; t[5] = s[9]; t[6] = s[14]; t[7] = s[3];
    t[8]  = s[8]; t[9] = s[13]; t[10] = s[2]; t[11] = s[7];
    t[12] = s[12]; t[13] = s[1]; t[14] = s[6]; t[15] = s[11];
    (void) _copy(s, sizeof(t), t, sizeof(t));
}