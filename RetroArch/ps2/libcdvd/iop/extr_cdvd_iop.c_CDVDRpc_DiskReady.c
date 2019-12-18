void *CDVDRpc_DiskReady(unsigned int *sbuff)
{
    int ret;

    if (isValidDisc())
        ret = sceCdDiskReady(sbuff[0]);
    else
        ret = -1;

    sbuff[0] = ret;
    return sbuff;
}