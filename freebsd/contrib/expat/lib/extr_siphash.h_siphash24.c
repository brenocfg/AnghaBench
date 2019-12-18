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
typedef  int /*<<< orphan*/  uint64_t ;
struct sipkey {int dummy; } ;
struct siphash {int dummy; } ;

/* Variables and functions */
 struct siphash SIPHASH_INITIALIZER ; 
 int /*<<< orphan*/  sip24_final (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sip24_init (struct siphash*,struct sipkey const*) ; 
 int /*<<< orphan*/  sip24_update (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static uint64_t siphash24(const void *src, size_t len,
		const struct sipkey *key) {
	struct siphash state = SIPHASH_INITIALIZER;
	return sip24_final(sip24_update(sip24_init(&state, key), src, len));
}