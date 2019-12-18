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

/* Variables and functions */

__attribute__((used)) static const char* Hash_Description(void) {
  return
    "The `Hash` class provides a mechanism for hashing an object. This hash "
    "value should remain the same across objects that are also considered "
    "equal by the `Cmp` class. For objects that are not considered equal this "
    "value should aim to be evenly distributed across integers."
    "\n\n"
    "This is not a cryptographic hash. It is used for various objects or "
    "data structures that require fast hashing such as the `Table` type. Due "
    "to this it should not be used for cryptography or security."
    "\n\n"
    "By default an object is hashed by using its raw memory with the "
    "[Murmurhash](http://en.wikipedia.org/wiki/MurmurHash) algorithm. Due to "
    "the link between them it is recommended to only override `Hash` and "
    "`Cmp` in conjunction.";
}