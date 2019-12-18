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
struct dio_submit {int dummy; } ;
struct dio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dio_get_page (struct dio*,struct dio_submit*) ; 
 scalar_t__ dio_pages_present (struct dio_submit*) ; 
 int /*<<< orphan*/  page_cache_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dio_cleanup(struct dio *dio, struct dio_submit *sdio)
{
	while (dio_pages_present(sdio))
		page_cache_release(dio_get_page(dio, sdio));
}