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
struct stir_cb {int /*<<< orphan*/  speed; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 scalar_t__ isfir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stir_fir_chars (struct stir_cb*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stir_sir_chars (struct stir_cb*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static inline void unwrap_chars(struct stir_cb *stir,
				const __u8 *bytes, int length)
{
	if (isfir(stir->speed))
		stir_fir_chars(stir, bytes, length);
	else
		stir_sir_chars(stir, bytes, length);
}