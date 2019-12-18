void *CDVDRpc_FindFile(unsigned int *sbuff)
{
    int ret;

    ret = CDVD_findfile((char *)&sbuff[0], (struct TocEntry *)&sbuff[1024 / 4]);

    sbuff[0] = ret;

    return sbuff;
}