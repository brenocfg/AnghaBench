#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zeros; int /*<<< orphan*/  chain; int /*<<< orphan*/  val; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ Hash ;

/* Variables and functions */
 int /*<<< orphan*/  lodepng_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hash_cleanup(Hash* hash)
{
  lodepng_free(hash->head);
  lodepng_free(hash->val);
  lodepng_free(hash->chain);
  lodepng_free(hash->zeros);
}