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
struct i2c_algo_pca_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_PCA_IND ; 
 int /*<<< orphan*/  I2C_PCA_INDPTR ; 
 int I2C_PCA_IPRESET ; 
 int /*<<< orphan*/  pca_outw (struct i2c_algo_pca_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pca9665_reset(void *pd)
{
	struct i2c_algo_pca_data *adap = pd;
	pca_outw(adap, I2C_PCA_INDPTR, I2C_PCA_IPRESET);
	pca_outw(adap, I2C_PCA_IND, 0xA5);
	pca_outw(adap, I2C_PCA_IND, 0x5A);
}