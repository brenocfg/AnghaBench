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
struct platform_device {int dummy; } ;
struct crypto_priv {int /*<<< orphan*/  reg; int /*<<< orphan*/  sram; int /*<<< orphan*/  sram_size; int /*<<< orphan*/  irq; int /*<<< orphan*/  queue_th; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cpg ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct crypto_priv*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct crypto_priv*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_aes_alg_cbc ; 
 int /*<<< orphan*/  mv_aes_alg_ecb ; 
 struct crypto_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mv_remove(struct platform_device *pdev)
{
	struct crypto_priv *cp = platform_get_drvdata(pdev);

	crypto_unregister_alg(&mv_aes_alg_ecb);
	crypto_unregister_alg(&mv_aes_alg_cbc);
	kthread_stop(cp->queue_th);
	free_irq(cp->irq, cp);
	memset(cp->sram, 0, cp->sram_size);
	iounmap(cp->sram);
	iounmap(cp->reg);
	kfree(cp);
	cpg = NULL;
	return 0;
}