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
#define  SHA1 129 
#define  SHA2_256 128 

__attribute__((used)) inline static size_t sha_engine_index(esp_sha_type type) {
    switch(type) {
    case SHA1:
        return 0;
    case SHA2_256:
        return 1;
    default:
        return 2;
    }
}