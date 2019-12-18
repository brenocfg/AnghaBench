#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mlx4_profile {int /*<<< orphan*/  num_mcg; } ;
struct TYPE_6__ {int /*<<< orphan*/  fw_icm; } ;
struct TYPE_5__ {int /*<<< orphan*/  inta_pin; } ;
struct mlx4_priv {TYPE_3__ fw; TYPE_2__ eq_table; } ;
struct mlx4_mod_stat_cfg {int log_pg_sz_m; scalar_t__ log_pg_sz; } ;
struct mlx4_init_hca_param {int log_uar_sz; int /*<<< orphan*/  hca_core_clock; scalar_t__ mw_enabled; scalar_t__ uar_page_sz; } ;
struct mlx4_dev_cap {int dummy; } ;
struct TYPE_4__ {scalar_t__ steering_mode; int max_fmr_maps; int flags; int bmme_flags; int flags2; int /*<<< orphan*/  hca_core_clock; int /*<<< orphan*/  num_uars; int /*<<< orphan*/  num_mpts; } ;
struct mlx4_dev {int /*<<< orphan*/  board_id; TYPE_1__ caps; } ;
struct mlx4_adapter {int /*<<< orphan*/  board_id; int /*<<< orphan*/  inta_pin; } ;
typedef  int /*<<< orphan*/  init_hca ;

/* Variables and functions */
 int EACCES ; 
 scalar_t__ INIT_HCA_TPT_MW_ENABLE ; 
 int MLX4_BMME_FLAG_TYPE_2_WIN ; 
 int MLX4_DEV_CAP_FLAG2_TS ; 
 int MLX4_DEV_CAP_FLAG_MEM_WINDOW ; 
 int /*<<< orphan*/  MLX4_FS_NUM_MCG ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  choose_steering_mode (struct mlx4_dev*,struct mlx4_dev_cap*) ; 
 struct mlx4_profile default_profile ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 scalar_t__ map_bf_area (struct mlx4_dev*) ; 
 scalar_t__ map_internal_clock (struct mlx4_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mlx4_init_hca_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_CLOSE_HCA (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int mlx4_INIT_HCA (struct mlx4_dev*,struct mlx4_init_hca_param*) ; 
 int mlx4_MOD_STAT_CFG (struct mlx4_dev*,struct mlx4_mod_stat_cfg*) ; 
 int mlx4_QUERY_ADAPTER (struct mlx4_dev*,struct mlx4_adapter*) ; 
 int mlx4_QUERY_FW (struct mlx4_dev*) ; 
 int mlx4_QUERY_HCA (struct mlx4_dev*,struct mlx4_init_hca_param*) ; 
 int /*<<< orphan*/  mlx4_UNMAP_FA (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*) ; 
 int mlx4_dev_cap (struct mlx4_dev*,struct mlx4_dev_cap*) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mlx4_free_icm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_icms (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_info (struct mlx4_dev*,char*) ; 
 int mlx4_init_icm (struct mlx4_dev*,struct mlx4_dev_cap*,struct mlx4_init_hca_param*,int) ; 
 int mlx4_init_slave (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int mlx4_load_fw (struct mlx4_dev*) ; 
 int mlx4_make_profile (struct mlx4_dev*,struct mlx4_profile*,struct mlx4_dev_cap*,struct mlx4_init_hca_param*) ; 
 int /*<<< orphan*/  mlx4_parav_master_pf_caps (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_set_port_mask (struct mlx4_dev*) ; 
 int mlx4_slave_cap (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_slave_exit (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  unmap_bf_area (struct mlx4_dev*) ; 
 int /*<<< orphan*/  unmap_internal_clock (struct mlx4_dev*) ; 

__attribute__((used)) static int mlx4_init_hca(struct mlx4_dev *dev)
{
	struct mlx4_priv	  *priv = mlx4_priv(dev);
	struct mlx4_adapter	   adapter;
	struct mlx4_dev_cap	   dev_cap;
	struct mlx4_mod_stat_cfg   mlx4_cfg;
	struct mlx4_profile	   profile;
	struct mlx4_init_hca_param init_hca;
	u64 icm_size;
	int err;

	if (!mlx4_is_slave(dev)) {
		err = mlx4_QUERY_FW(dev);
		if (err) {
			if (err == -EACCES)
				mlx4_info(dev, "non-primary physical function, skipping.\n");
			else
				mlx4_err(dev, "QUERY_FW command failed, aborting.\n");
			return err;
		}

		err = mlx4_load_fw(dev);
		if (err) {
			mlx4_err(dev, "Failed to start FW, aborting.\n");
			return err;
		}

		mlx4_cfg.log_pg_sz_m = 1;
		mlx4_cfg.log_pg_sz = 0;
		err = mlx4_MOD_STAT_CFG(dev, &mlx4_cfg);
		if (err)
			mlx4_warn(dev, "Failed to override log_pg_sz parameter\n");

		err = mlx4_dev_cap(dev, &dev_cap);
		if (err) {
			mlx4_err(dev, "QUERY_DEV_CAP command failed, aborting.\n");
			goto err_stop_fw;
		}

		choose_steering_mode(dev, &dev_cap);

		if (mlx4_is_master(dev))
			mlx4_parav_master_pf_caps(dev);

		profile = default_profile;
		if (dev->caps.steering_mode ==
		    MLX4_STEERING_MODE_DEVICE_MANAGED)
			profile.num_mcg = MLX4_FS_NUM_MCG;

		icm_size = mlx4_make_profile(dev, &profile, &dev_cap,
					     &init_hca);
		if ((long long) icm_size < 0) {
			err = icm_size;
			goto err_stop_fw;
		}

		dev->caps.max_fmr_maps = (1 << (32 - ilog2(dev->caps.num_mpts))) - 1;

		init_hca.log_uar_sz = ilog2(dev->caps.num_uars);
		init_hca.uar_page_sz = PAGE_SHIFT - 12;
		init_hca.mw_enabled = 0;
		if (dev->caps.flags & MLX4_DEV_CAP_FLAG_MEM_WINDOW ||
		    dev->caps.bmme_flags & MLX4_BMME_FLAG_TYPE_2_WIN)
			init_hca.mw_enabled = INIT_HCA_TPT_MW_ENABLE;

		err = mlx4_init_icm(dev, &dev_cap, &init_hca, icm_size);
		if (err)
			goto err_stop_fw;

		err = mlx4_INIT_HCA(dev, &init_hca);
		if (err) {
			mlx4_err(dev, "INIT_HCA command failed, aborting.\n");
			goto err_free_icm;
		}
		/*
		 * If TS is supported by FW
		 * read HCA frequency by QUERY_HCA command
		 */
		if (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_TS) {
			memset(&init_hca, 0, sizeof(init_hca));
			err = mlx4_QUERY_HCA(dev, &init_hca);
			if (err) {
				mlx4_err(dev, "QUERY_HCA command failed, disable timestamp.\n");
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
			} else {
				dev->caps.hca_core_clock =
					init_hca.hca_core_clock;
			}

			/* In case we got HCA frequency 0 - disable timestamping
			 * to avoid dividing by zero
			 */
			if (!dev->caps.hca_core_clock) {
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
				mlx4_err(dev,
					 "HCA frequency is 0. Timestamping is not supported.");
			} else if (map_internal_clock(dev)) {
				/*
				 * Map internal clock,
				 * in case of failure disable timestamping
				 */
				dev->caps.flags2 &= ~MLX4_DEV_CAP_FLAG2_TS;
				mlx4_err(dev, "Failed to map internal clock. Timestamping is not supported.\n");
			}
		}
	} else {
		err = mlx4_init_slave(dev);
		if (err) {
			mlx4_err(dev, "Failed to initialize slave\n");
			return err;
		}

		err = mlx4_slave_cap(dev);
		if (err) {
			mlx4_err(dev, "Failed to obtain slave caps\n");
			goto err_close;
		}
	}

	if (map_bf_area(dev))
		mlx4_dbg(dev, "Failed to map blue flame area\n");

	/*Only the master set the ports, all the rest got it from it.*/
	if (!mlx4_is_slave(dev))
		mlx4_set_port_mask(dev);

	err = mlx4_QUERY_ADAPTER(dev, &adapter);
	if (err) {
		mlx4_err(dev, "QUERY_ADAPTER command failed, aborting.\n");
		goto unmap_bf;
	}

	priv->eq_table.inta_pin = adapter.inta_pin;
	memcpy(dev->board_id, adapter.board_id, sizeof dev->board_id);

	return 0;

unmap_bf:
	unmap_internal_clock(dev);
	unmap_bf_area(dev);

err_close:
	if (mlx4_is_slave(dev))
		mlx4_slave_exit(dev);
	else
		mlx4_CLOSE_HCA(dev, 0);

err_free_icm:
	if (!mlx4_is_slave(dev))
		mlx4_free_icms(dev);

err_stop_fw:
	if (!mlx4_is_slave(dev)) {
		mlx4_UNMAP_FA(dev);
		mlx4_free_icm(dev, priv->fw.fw_icm, 0);
	}
	return err;
}