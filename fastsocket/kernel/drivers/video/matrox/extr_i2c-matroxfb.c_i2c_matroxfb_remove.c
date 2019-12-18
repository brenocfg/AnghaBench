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
struct matroxfb_dh_maven_info {int dummy; } ;
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_ddc1_done (struct matroxfb_dh_maven_info*) ; 
 int /*<<< orphan*/  i2c_ddc2_done (struct matroxfb_dh_maven_info*) ; 
 int /*<<< orphan*/  i2c_maven_done (struct matroxfb_dh_maven_info*) ; 
 int /*<<< orphan*/  kfree (struct matroxfb_dh_maven_info*) ; 

__attribute__((used)) static void i2c_matroxfb_remove(struct matrox_fb_info* minfo, void* data) {
	struct matroxfb_dh_maven_info* m2info = data;

	i2c_maven_done(m2info);
	i2c_ddc2_done(m2info);
	i2c_ddc1_done(m2info);
	kfree(m2info);
}