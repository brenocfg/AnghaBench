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
 int /*<<< orphan*/  CMO_CHARACTERISTICS_TOKEN ; 
 int CMO_MAXLENGTH ; 
 int CMO_PageSize ; 
 int CMO_PrPSP ; 
 int CMO_SecPSP ; 
 int /*<<< orphan*/  FW_FEATURE_CMO ; 
 int IOMMU_PAGE_SHIFT ; 
 int /*<<< orphan*/  RTAS_DATA_BUF_SIZE ; 
 int /*<<< orphan*/  __pa (char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pSeries_coalesce_init () ; 
 int /*<<< orphan*/  powerpc_firmware_features ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int rtas_call (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* rtas_data_buf ; 
 int /*<<< orphan*/  rtas_data_buf_lock ; 
 int /*<<< orphan*/  rtas_token (char*) ; 
 int simple_strtol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 

void pSeries_cmo_feature_init(void)
{
	char *ptr, *key, *value, *end;
	int call_status;
	int page_order = IOMMU_PAGE_SHIFT;

	pr_debug(" -> fw_cmo_feature_init()\n");
	spin_lock(&rtas_data_buf_lock);
	memset(rtas_data_buf, 0, RTAS_DATA_BUF_SIZE);
	call_status = rtas_call(rtas_token("ibm,get-system-parameter"), 3, 1,
				NULL,
				CMO_CHARACTERISTICS_TOKEN,
				__pa(rtas_data_buf),
				RTAS_DATA_BUF_SIZE);

	if (call_status != 0) {
		spin_unlock(&rtas_data_buf_lock);
		pr_debug("CMO not available\n");
		pr_debug(" <- fw_cmo_feature_init()\n");
		return;
	}

	end = rtas_data_buf + CMO_MAXLENGTH - 2;
	ptr = rtas_data_buf + 2;	/* step over strlen value */
	key = value = ptr;

	while (*ptr && (ptr <= end)) {
		/* Separate the key and value by replacing '=' with '\0' and
		 * point the value at the string after the '='
		 */
		if (ptr[0] == '=') {
			ptr[0] = '\0';
			value = ptr + 1;
		} else if (ptr[0] == '\0' || ptr[0] == ',') {
			/* Terminate the string containing the key/value pair */
			ptr[0] = '\0';

			if (key == value) {
				pr_debug("Malformed key/value pair\n");
				/* Never found a '=', end processing */
				break;
			}

			if (0 == strcmp(key, "CMOPageSize"))
				page_order = simple_strtol(value, NULL, 10);
			else if (0 == strcmp(key, "PrPSP"))
				CMO_PrPSP = simple_strtol(value, NULL, 10);
			else if (0 == strcmp(key, "SecPSP"))
				CMO_SecPSP = simple_strtol(value, NULL, 10);
			value = key = ptr + 1;
		}
		ptr++;
	}

	/* Page size is returned as the power of 2 of the page size,
	 * convert to the page size in bytes before returning
	 */
	CMO_PageSize = 1 << page_order;
	pr_debug("CMO_PageSize = %lu\n", CMO_PageSize);

	if (CMO_PrPSP != -1 || CMO_SecPSP != -1) {
		pr_info("CMO enabled\n");
		pr_debug("CMO enabled, PrPSP=%d, SecPSP=%d\n", CMO_PrPSP,
		         CMO_SecPSP);
		powerpc_firmware_features |= FW_FEATURE_CMO;
		pSeries_coalesce_init();
	} else
		pr_debug("CMO not enabled, PrPSP=%d, SecPSP=%d\n", CMO_PrPSP,
		         CMO_SecPSP);
	spin_unlock(&rtas_data_buf_lock);
	pr_debug(" <- fw_cmo_feature_init()\n");
}