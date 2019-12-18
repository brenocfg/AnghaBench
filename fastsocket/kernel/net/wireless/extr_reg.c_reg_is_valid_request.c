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
struct regulatory_request {int /*<<< orphan*/  alpha2; scalar_t__ processed; } ;

/* Variables and functions */
 int alpha2_equal (int /*<<< orphan*/ ,char const*) ; 
 struct regulatory_request* get_last_request () ; 

__attribute__((used)) static bool reg_is_valid_request(const char *alpha2)
{
	struct regulatory_request *lr = get_last_request();

	if (!lr || lr->processed)
		return false;

	return alpha2_equal(lr->alpha2, alpha2);
}