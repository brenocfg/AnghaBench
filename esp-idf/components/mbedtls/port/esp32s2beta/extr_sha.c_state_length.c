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
typedef  int esp_sha_type ;

/* Variables and functions */
#define  SHA1 132 
#define  SHA2_224 131 
#define  SHA2_256 130 
#define  SHA2_384 129 
#define  SHA2_512 128 

__attribute__((used)) inline static size_t state_length(esp_sha_type type) {
    switch(type) {
    case SHA1:
        return 160/8;
    case SHA2_224:
    case SHA2_256:
        return 256/8;
    case SHA2_384:
    case SHA2_512:
        return 512/8;
    default:
        return 0;
    }
}